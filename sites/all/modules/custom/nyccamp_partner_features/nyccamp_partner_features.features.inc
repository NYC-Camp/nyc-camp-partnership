<?php
/**
 * @file
 * nyccamp_partner_features.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function nyccamp_partner_features_commerce_product_default_types() {
  $items = array(
    'individual_partnership' => array(
      'type' => 'individual_partnership',
      'name' => 'Individual Partnership',
      'description' => 'Individual Partnership are for individuals who wish to sponsor NYC Camp.',
      'help' => '',
      'revision' => 1,
    ),
    'partnership' => array(
      'type' => 'partnership',
      'name' => 'Partnership',
      'description' => 'A Basic Partnership is a type of sponsorship for NYC Camp',
      'help' => '',
      'revision' => 1,
    ),
    'tier_partnership' => array(
      'type' => 'tier_partnership',
      'name' => 'Tier Partnership',
      'description' => 'Tier Partnerships are overall sponsorships for NYC Camp.',
      'help' => '',
      'revision' => 1,
    ),
    'title_partnership' => array(
      'type' => 'title_partnership',
      'name' => 'Title Partnership',
      'description' => 'Title Partnerships are sponsors for a particular event during NYC Camp.',
      'help' => '',
      'revision' => 1,
    ),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function nyccamp_partner_features_node_info() {
  $items = array(
    'keynote_benefit' => array(
      'name' => t('Keynote Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Keynote Benefit</em> is a type of partnership benefit that pertains to the NYC Camp keynote.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'other_benefit' => array(
      'name' => t('Other Benefit'),
      'base' => 'node_content',
      'description' => t('An<em>Other Benefit</em> is a type of partnership benefit that pertains to a miscellaneous NYC Camp benefit.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'partner_pavilion_benefit' => array(
      'name' => t('Partner Pavilion Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Partner Pavilion Benefit</em> is a type of partnership benefit that pertains to the NYC Camp partner pavilion area.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'program_benefit' => array(
      'name' => t('Program Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Program Benefit</em> is a type of partnership benefit that pertains to the NYC Camp printed program.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'signage_benefit' => array(
      'name' => t('Signage Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Signage Benefit</em> is a type of partnership benefit that pertains to the NYC Camp printed and digital signage.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'social_media_benefit' => array(
      'name' => t('Social Media Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Social Media Benefit</em> is a type of partnership benefit that pertains to NYC Camp social media.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'summit_benefit' => array(
      'name' => t('Summit Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Summit Benefit</em> is a type of partnership benefit that pertains to the NYC Camp summits.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'swag_benefit' => array(
      'name' => t('Swag Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Swag Benefit</em> is a type of partnership benefit that pertains to NYC Camp swag.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
    'website_benefit' => array(
      'name' => t('Website Benefit'),
      'base' => 'node_content',
      'description' => t('A <em>Website Benefit</em> is a type of partnership benefit that pertains to the NYC Camp web properties.'),
      'has_title' => '1',
      'title_label' => t('Key'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
