<?php


/**
 * @file
 * Plugin to provide access control based on the branch context and overrides.
 */

$plugin = array(
  'title' => t("Zariz: Is overriden"),
  'description' => t('Determine if override is defined for the objecy.'),
  'callback' => 'zariz_override_ctools_check_override',
  'default' => array(
    'object_type' => 'variable',
    'object_id' => '',
  ),
  'settings form' => 'zariz_override_ctools_access_settings',
  'summary' => 'zariz_override_ctools_access_summary',
);

/**
 * Settings form for the 'by perm' access plugin
 */
function zariz_override_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['object_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Object type'),
    '#default_value' => $conf['object_type'],
    '#description' => t('Select the object type, e.g. "varialbe".'),
    '#required' => TRUE,
  );

  $form['settings']['object_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Object ID'),
    '#default_value' => $conf['object_id'],
    '#description' => t('Select the object ID, e.g. "site_info".'),
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Check for access.
 */
function zariz_override_ctools_check_override($conf, $context) {
  if (!$og_context = og_context()) {
    // No context, so allow access.
    return TRUE;
  }

  $branch_id = $og_context['gid'];
  $object_type = $conf['object_type'];
  $object_ids = array($conf['object_id']);

  return zariz_override_get_overrides($branch_id, $object_type, $object_ids);
}

/**
 * Provide a summary description.
 */
function zariz_override_ctools_access_summary($conf, $context) {
  $params = array(
    '@object_type' => $conf['object_type'],
    '@object_id' => $conf['object_id'],
  );
  return t('Zariz overrides @object_type with ID @object_id.', $params);
}

