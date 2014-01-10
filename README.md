[![Build Status](https://travis-ci.org/Gizra/zariz.png?branch=master)](https://travis-ci.org/Gizra/zariz)

# Content Staging module suite for Drupal 7.x

Zariz is a suite of Drupal modules and methodology, that models content (nodes)
creation and editing similar to Git's branches, and allows generating static
sites from the Drupal backend. You can read more about it in [this](http://www.gizra.com/content/zariz-means-agile/)
blog post, and [here](http://www.gizra.com/content/zariz-in-pics/).

The counterpart of Zariz which is responsible for the static site creation is
[generator-zariz](https://npmjs.org/package/generator-zariz).

### Creating branch

The OG (Organic groups) group type ``Branch`` is equivalent to a Git branch.

```php
// Create a new "master" branch. There can be only a single master on the site.
$live_node = zariz_create_branch('live');

// Branch out fom the live branch.
$dev_node = zariz_create_branch('dev', $live_node);
```

### Merging branches

We can check if there are merge conflicts - meaning that there is already a newer
content in the "to branch". Zariz will auto-detect the parent branch.

```php
$conflicts = zariz_get_merge_conflicts($dev_node->nid);
```

If there are no conflicts, we can merge - meaning that content from the "from
branch" will be cloned into the "to branch".

```php
$snapshot = zariz_merge_branch($dev_node->nid);
```

### Working with Snapshots

Snapshots holds information about the content of a branch at a certain time.
This is done by simply holding the last node ID that existed. The last node ID
can keep changing as long as the snapshot is not locked. Once the snapshot is
locked it can no longer change.

```php
// Get the last snapshot from a branch.
$snapshot = zariz_get_snapshot_from_branch($live_node->nid);

// Check if a snapshot is locked.
$snpashot->isLocked()

// Locking a snpashot.
$snpashot->lock()
```

### Query alter

Zariz can alter a query to the node table, to referlect the content in a certain branch.
The altering is opt-in, by settings the ``zariz`` query tag. For example:

```php
$query = new EntityFieldQuery();
$result = $query
  ->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'article')
  // Set the Zariz query tag.
  ->addTag('zariz')
  // Set explicetly the Branch ID. If this Metadata is ommitted, the
  // OG-context will be used.
  ->addMetaData('zariz', array('branch_id' => $branch_id))
  ->propertyOrderBy('nid')
  ->execute();
```

### Dependencies

Unless stated otherwise, use latest release version is required.

* [Entity reference prepopualte](https://drupal.org/project/entityreference_prepopulate) 
* [Organic groups](https://drupal.org/project/og) (Dev version until [this](https://drupal.org/node/2162861) bug in Drupal.org release managment is fixed)
* [Replicate](https://drupal.org/project/replicate)
* [Node clone](https://drupal.org/project/node_clone)

Here is the Drush command to download and install Zariz UI:
```
drush dl entityreference_prepopulate replicate node_clone
drush dl og --dev
drush en zariz_ui
```

### Typical permissions setup

* In ``admin/people/permissions`` grant authenticated user ``Branch: Create new content``
* In ``admin/config/group/permissions/node/branch`` grant non-member and member roles the following permissions:
 * ``Merge branch``
 * ``Create Article content``
 * ``Edit any Article content``


### Example module

Enable ``zariz_example`` module and follow it's [README](https://github.com/Gizra/zariz/blob/7.x-1.x/modules/zariz_example/README.md)

Developed by [Gizra](http://gizra.com)
