Zariz Revision Control module suite for Drupal 7.x

Key concepts and terminology:

* Based on Organic groups
* The group type ``Branch`` is equivalent to a Git branch
* Like Git, content can be merged from one branch to another. 
* A ``Snapshot`` entity keeps track of the last node ID that was created in a branch at a certain time. Multiple Snapshots can exist in a Branch, each pointing to their parent snapshot.
* Zariz's is very strict about data integrity, and will throw Exceptions whenever trying to tamper with it
* The counterpart of Zariz is [generator-zariz](https://npmjs.org/package/generator-zariz)

Developed by [Gizra](http://gizra.com)
