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
    return TRUE;
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
}
