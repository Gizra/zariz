<?php

/**
 * @file
 * Main class for Tree entities provided by Entity API.
 */

class Tree extends Entity {
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'tree');
  }
}
