<?php

/**
 * @file
 * Contains ZarizEntityReferenceBehavior
 */

class ZarizEntityReferenceBehavior extends EntityReference_BehaviorHandler_Abstract {

  /**
   * Overrides EntityReference_BehaviorHandler_Abstract::access().
   */
  public function access($field, $instance) {
    return $field['settings']['handler'] == 'zariz' || strpos($field['settings']['handler'], 'zariz_') === 0;
  }

  /**
   * Overrides EntityReference_BehaviorHandler_Abstract::schema_alter().
   *
   * Add UUID field.
   */
  public function schema_alter(&$schema, $field) {
    $schema['columns']['uuid'] = array(
      'description' => 'The UUID of the referenced entity.',
      'type' => 'varchar',
      'length' => 128,
      'not null' => FALSE,
      'default' => NULL,
    );
  }

  /**
   * Overrides EntityReference_BehaviorHandler_Abstract::presave().
   *
   * Add UUID along with the referenced entity ID.
   */
  public function presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
    $field_name = $field['field_name'];
    $cardinality = $field['cardinality'];

    $wrapper = entity_metadata_wrapper($entity_type, $entity);

    $uuids = array();

    if ($cardinality == 1) {
      if ($id = $wrapper->{$field_name}->getIdentifier()) {
        $uuids[$id] = $wrapper->{$field_name}->field_uuid->value();
      }
    }
    else {
      foreach ($wrapper->{$field_name} as $sub_wrapper) {
        $id = $sub_wrapper->getIdentifier();
        $uuids[$id] = $sub_wrapper->field_uuid->value();
      }
    }


    foreach ($items as &$item) {
      if (empty($item['target_id'])) {
        $item['uuid'] = NULL;
      }
      else {
        $id = $item['target_id'];
        $item['uuid'] = $uuids[$id];
      }
    }
  }
}
