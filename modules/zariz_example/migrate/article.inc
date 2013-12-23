<?php

/**
 * Contains ZarizExampleArticleNodes
 */


class ZarizExampleArticleNodes extends ZarizExampleMigration {
  public $csvColumns = array(
    array('body', 'Body'),
    array('created', 'Posted'),
    array('field_image', 'Image')
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

    // Add content to the master branch.
    $master_nid = variable_get('zariz_master_branch');
    $this
      ->addFieldMapping('field_branch')
      ->defaultValue($master_nid);
  }
}
