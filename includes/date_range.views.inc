<?php

require_once dirname(__FILE__) . '/common.inc';

function hook_views_query_alter(&$view, &$query) {
//  drupal_set_message('<pre>'. print_r($query, 1) .'</pre>');
}
