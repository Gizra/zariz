<?php

/**
 * @file
 * Main class for Snapshot entities provided by Entity API.
 */

class Snapshot extends Entity {
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'snapshot');
  }

  /**
   * Lock a Snapshot to prevent further editing.
   */
  public function lock() {
    $this->locked = TRUE;
    $this->_allow_locked_save = TRUE;
    $this->save();
  }

  /**
   * Return TRUE is snapshot if locked for editing.
   */
  public function isLocked() {
    return !empty($this->locked);
  }

  /**
   * Overrides Entity::save().
   *
   * Prevent re-saving of locked Snapshots.
   */
  public function save() {
    if ($this->isLocked() && empty($this->_allow_locked_save)) {
      throw new Exception('A locked snapshot cannot be saved.');
    }

    unset($this->_allow_locked_save);
    parent::save();
  }
}
