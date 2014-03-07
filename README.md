[![Build Status](https://travis-ci.org/Gizra/zariz.png?branch=7.x-1.x)](https://travis-ci.org/Gizra/zariz)

# "Site preview" module suite for Drupal 7.x

Zariz is a suite of Drupal modules and methodology, that models content (nodes)
creation and editing similar to Git's branches, and allows generating static
sites from the Drupal backend.

The counterpart of Zariz which is responsible for the static site creation is
[generator-zariz](https://npmjs.org/package/generator-zariz).

## Posts and videos

* [Zariz in pics](http://www.gizra.com/content/zariz-in-pics/)
* [Drupal, only x5 faster](http://www.gizra.com/content/drupal-x5-faster/)
* Video - [jam's Drupal Camp session: Zariz - Continuous Deployment for Content](http://www.youtube.com/watch?v=vGUSXwURVVo&feature=share&t=15m39s)

## Live Demo

1. Launch a sandbox in http://simplytest.me/project/zariz/7.x-1.x
2. Navigate to ``/live/user`` and login (user: admin pass: admin)
3. Navigate to ``admin/content/migrate`` and migate the content
4. Back in the homepage, you can now branch, create and edit content, and merge

## Creating branch

The OG (Organic groups) group type ``Branch`` is equivalent to a Git branch.

```php
// Create a new "master" branch. There can be only a single master on the site.
$live_node = zariz_create_branch('live');

// Branch out fom the live branch.
$dev_node = zariz_create_branch('dev', $live_node);
```

## Merging branches

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

## Working with Snapshots

Snapshots holds information about the content of a branch at a certain time.
This is done by simply holding the last entity ID (e.g. node) that existed. The last entity ID can keep changing as long as the snapshot is not locked.

```php
// Get the last snapshot from a branch.
$snapshot = zariz_get_snapshot_from_branch($live_node->nid);

// Check if a snapshot is locked.
$snpashot->isLocked()

// Lock a snpashot.
$snpashot->lock()
```

## Query alter

Zariz can alter a query to the node table, to reflect the content in a certain branch.
The altering is opt-in, by settings the ``zariz`` query tag. For example:

```php
$query = new EntityFieldQuery();
$result = $query
  ->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'article')
  // Set the Zariz query tag.
  ->addTag('zariz')
  // Set explicitly the Branch ID. If this Metadata is omitted, the
  // OG-context will be used.
  ->addMetaData('zariz', array('branch_id' => $branch_id))
  ->propertyOrderBy('nid')
  ->execute();
```

The same query tag can be also used in Views. For example in ``/admin/structure/views/view/branch_content/edit`` under ``Query settings`` => ``Query Tags`` notice that the ``zariz`` tag was added.

## Dependencies

* [Entity reference prepopualte](https://drupal.org/project/entityreference_prepopulate)
* [Node clone](https://drupal.org/project/node_clone)
* [Organic groups](https://drupal.org/project/og)
* [Replicate](https://drupal.org/project/replicate)
* (optional) [Commerce](https://drupal.org/project/commerce) - dev version


### Commerce integration
"Zariz commerce" module integrates with commerce and allows smart revisioning
of commerce products.

## Typical permissions setup

* In ``admin/people/permissions`` grant authenticated user ``Branch: Create new content``
* In ``admin/config/group/permissions/node/branch`` grant non-member and member roles the following permissions:
 * ``Merge branch``
 * ``Create Article content``
 * ``Edit any Article content``

## Example module

Enable ``zariz_example`` module and follow its [README](https://github.com/Gizra/zariz/blob/7.x-1.x/modules/zariz_example/README.md)
Here is the Drush command to download and install Zariz Example:
```
drush dl entityreference_prepopulate replicate node_clone
drush dl og --dev
drush en zariz_example
```

Developed by [Gizra](http://gizra.com)
