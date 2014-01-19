<?php

/**
 * Contains ZarizExampleArticleNodes
 */


class ZarizExampleArticleNodes extends ZarizExampleMigration {
  public $csvColumns = array(
    array('body', 'Body'),
    array('created', 'Posted'),
    array('field_image', 'Image'),
    array('field_zariz_node', 'Content'),
  );

  public $entityType = 'node';
  public $bundle = 'article';

  public function __construct() {
    parent::__construct();

    $this
      ->addFieldMapping('body', 'body')
      ->arguments(array('format' => 'plain_text'));

    $this->addFieldMapping('created', 'created');

    $this->addFieldMapping('field_image', 'field_image');

    $this
      ->addFieldMapping('field_image:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);

    $this
      ->addFieldMapping('field_image:source_dir')
      ->defaultValue(drupal_get_path('module', 'zariz_example') . '/migrate/images');


    $this
      ->addFieldMapping('field_zariz_node', 'field_zariz_node')
      ->sourceMigration('ZarizExampleArticleNodes')
      ->separator('|');

    // Add content to the master branch.
    $master_nid = variable_get('zariz_master_branch');

    $this
      ->addFieldMapping('field_branch')
      ->defaultValue($master_nid);

    // No comments.
    $this
      ->addFieldMapping('comment')
      ->defaultValue(COMMENT_NODE_CLOSED);

    // Author should be user ID 1.
    $this
      ->addFieldMapping('uid')
      ->defaultValue(1);
  }
}
