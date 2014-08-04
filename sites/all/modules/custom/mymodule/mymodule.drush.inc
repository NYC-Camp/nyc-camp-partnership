<?php
/**
 * Implementation of hook_drush_command().
 */
function mymodule_drush_command() {
  $items = array();
  // Name of the drush command.
  $items['list-site-users'] = array(
    'description' => 'Print the list of users in the site',
    'callback' => 'drush_get_site_users',
  );
  return $items;
}
 
function drush_get_site_users() {
  $query = db_select('users', 'u');
  $query->fields('u', array('name'));
  $result = $query->execute();
  while($record = $result->fetchAssoc()) {
       print_r($record['name']);
  }
}
