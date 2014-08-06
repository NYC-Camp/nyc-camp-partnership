<?php

/**
 * Implements hook_drush_command().
 */
function nyccamp_partner_drush_command()
{
    $items = array();
    $items["update-partnerships"] = array(
        "description" => "Updates the partnerships for the site",
        "callback" => "drush_update_partnerships",
    );
    $items["update-benefits"] = array(
        "description" => "Updates the partnership benefits for the site",
        "callback" => "drush_update_benefits",
    );
    return $items;
}

function drush_update_partnerships()
{
    $benefits_cache = array();
    $benefit_types = array(
        "program_benefit",
        "signage_benefit",
        "website_benefit",
        "partner_pavilion_benefit",
        "summit_benefit",
        "social_media_benefit",
        "keynote_benefit",
        "swag_benefit",
        "other_benefit",
    );
    $lib_detect = libraries_detect("spyc");
    if(empty($lib_detect["installed"])) {
        drush_log("Missing Spyc library.", "error");
        return;
    }

    $library = libraries_load("spyc");
    $partnerships = Spyc::YAMLLoad(drupal_get_path("module", "nyccamp_partner") . '/partnership-options/partnerships.yml');
    foreach($partnerships as $partnership_type => $partnership_options)
    {
        foreach($partnership_options as $partnership_option_name => $partnership_option)
        {
            if(commerce_product_load_by_sku($partnership_option_name) == false) {
                $partnership = commerce_product_new($partnership_type);
                $pwrapper = entity_metadata_wrapper("commerce_product", $partnership);
                $pwrapper->uid->set(1);
                $pwrapper->sku->set($partnership_option_name);
                $pwrapper->title->set($partnership_option["title"]);
                $pwrapper->language->set(LANGUAGE_NONE);
                $pwrapper->commerce_price->set(array(
                            "amount" => $partnership_option["price"],
                            "currency_code" => "USD",
                        ));
                $pwrapper->commerce_stock->set($partnership_option["stock"]);
                if(array_key_exists("view_order", $partnership_option)) {
                    $pwrapper->field_view_order->set($partnership_option["view_order"]);
                }

                // Sets the benefits for the partnership
                foreach($benefit_types as $benefit_type)
                {
                    // Check to ensure the benefit is actually there
                    if(array_key_exists($benefit_type, $partnership_option)) {
                        $benefits = array();
                        foreach($partnership_option[$benefit_type] as $index => $benefit_key)
                        {
                            $benefit = nyccamp_partner_check_benefit($benefit_key, $benefit_type);
                            if($benefit == false) {
                                drush_log(
                                    sprintf("%s of type %s does not exist!", $benefit_key, $benefit_type),
                                    "error"
                                );
                                continue;
                            }
                            $benefits[] = intval($benefit->nid);
                        }
                        $benefit_type_field = "field_" . $benefit_type;
                        $pwrapper->$benefit_type_field->set($benefits);
                    }
                }
                $pwrapper->save();
                drush_log(sprintf("%s created.\n", $partnership_option_name), "ok");
            } else {
                drush_log(sprintf("Already Exists: %s", $partnership_option_name));
            }
        }
    }
    drush_log("Partnership updates complete.", "success");
    // $example = commerce_product_load_by_sku("level-one-conference-partner-2");
    // print_r($example);

}

function drush_update_benefits()
{
    $lib_detect = libraries_detect("spyc");
    if(empty($lib_detect["installed"])) {
        drush_log("Missing Spyc library.", "error");
        return;
    }
    libraries_load("spyc");
    $benefits = Spyc::YAMLLoad(drupal_get_path("module", "nyccamp_partner") . "/partnership-options/benefits.yml");
    foreach($benefits as $benefit_type => $benefit_options)
    {
        foreach($benefit_options as $benefit_option_key => $benefit_option)
        {
            if(nyccamp_partner_check_benefit($benefit_option_key, $benefit_type) == false) {
                $benefit = nyccamp_partner_create_node($benefit_type);
                $bwrapper = entity_metadata_wrapper("node", $benefit);
                $bwrapper->title->set($benefit_option_key);
                $bwrapper->field_benefit->set($benefit_option["benefit"]);
                if(array_key_exists("details", $benefit_option)) {
                    $bwrapper->field_details->set($benefit_option["details"]);
                }
                $bwrapper->save();
                drush_log(sprintf("%s of type %s created.\n", $benefit_option_key, $benefit_type), "ok");
            } else {
                drush_log(sprintf("Already Exists: %s of type: %s", $benefit_option_key, $benefit_type));
            }
        }
    }
    drush_log("Benefit updates complete.", "success");
}

/**
 * Takes the key for the benefit and returns a boolean indicating if it has been
 * created
 * @param string $key
 *  The key for the benefit
 * @param string $benefit_type
 *  The node type of this benefit
 * @return bool
 */
function nyccamp_partner_check_benefit($key, $benefit_type)
{
    $query = new EntityFieldQuery();
    $entities = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', $benefit_type)
        ->propertyCondition('title', $key)
        ->propertyCondition('status', 1)
        ->range(0,1)
        ->execute();
    if (!empty($entities['node'])) {
        $node = node_load(current(array_keys($entities['node'])));
        return $node;
    }
    return false;
}

function nyccamp_partner_create_node($type)
{
    $values = array(
        "type" => $type,
        "uid" => 1,
        "status" => 1,
        "comment" => 0,
        "promote" => 0,
    );
    $entity = entity_create("node", $values);
    return $entity;
}
