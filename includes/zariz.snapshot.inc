<?php

/**
 * @file
 * Main class for Snapshot entities provided by Entity API.
 */

class Snapshot extends Entity {
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'snapshot');
  }
}
