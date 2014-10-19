
# NYC Partners
---------------

## System Summary
* Drops 7
    * https://github.com/pantheon-systems/drops-7
* Drupal Commerce
   * https://www.drupal.org/project/commerce
* Aurora (base theme)
    * http://snugug.github.io/Aurora/
* nyc_camp_partnership (sub-theme of Aurora)
    * generated with https://github.com/Snugug/generator-aurora/

## Getting Started - Theming
* install **node.js** http://nodejs.org/download/
* `cd sites/all/themes/nyc_camp_partnership`
* `sudo npm install`
* `bower install`
* `bundle install`

**Warning** some of the dependencies that get installed in the node_modules and .vendor directories contain .info files, Drupal does not like this **especially** when clearing your cache. To mitigate this run (from `sites/all/themes/nyc_camp_partnership`):

`find ./node_modules ./.vendor -name "*.info" -exec rm {} ’;’`

### To begin theming
* from `sites/all/themes/nyc_camp_partnership` run `gulp server`
* **Gulp.js** handles all task running (Sass compiling, JS linting, etc.)
