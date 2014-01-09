### Manual Installation

* Enable module
* Migrate demo content via ``admin/content/migrate``
* Click on the home page and be redirected to the "master" branch
* Create a new branch, add new article, or editing an existing one, and then
merge work back to the live

### Installation using Drush

```bash
# Re-install the Drupal site.
drush si --account-pass=admin -y
# Enable Zariz example module.
drush en zariz_example -y
# Optional, Enable Zariz static module.
drush en zariz_static -y
# Migrate demo content
drush mi --all
```
