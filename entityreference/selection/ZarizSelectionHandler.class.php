<?php

/**
 * @file
 * Contains ZarizSelectionHandler.
 */

class ZarizSelectionHandler extends EntityReference_SelectionHandler_Generic {

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new self($field, $instance, $entity_type, $entity);
  }

  /**
   * Overrides EntityReference_SelectionHandler_Generic::settingsForm().
   */
  public static function settingsForm($field, $instance) {
    $form = EntityReference_SelectionHandler_Generic::settingsForm($field, $instance);
    if (!empty($form['target_bundles'])) {
      $target_type = $field['settings']['target_type'];
      $form['target_bundles']['#options'] = zariz_get_group_content_bundles($target_type);
    }

    return $form;
  }

  /**
   * Overrides EntityReference_SelectionHandler_Generic::buildEntityFieldQuery().
   *
   * Adds the "zariz" tag to the query.
   */
  public function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    $handler = EntityReference_SelectionHandler_Generic::getInstance($this->field, $this->instance, $this->entity_type, $this->entity);
    $query = $handler->buildEntityFieldQuery($match, $match_operator);

    $query->addTag('zariz');


    return $query;
  }
}
