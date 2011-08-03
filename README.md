#Drupal Content Reservation Module

## URL Scheme
* /reservations/r/$action_type/$key
	* /reservations/r/type/$content_type
	* /reservations/r/id/$content_id
	* /reservations/r/edit/$reservation_id
* /reservations/j/$query_type/$query_key - Returns an array of fullcalender event objects formatted as json, $query_type is one of either type, nid, uid and $query_key is the appropriate type or id to search for.

## DB Fields
* Reservation Id (rid)
* Associated Node Id (nid)
* Associated User Id (uid)
* Start DateTime (start)
* End DateTime (end)
* Purpose (description)
* Moderation Status (status)
* Created (created)
* Modified (modified)

## Installation Notes
If you download the latest dev version there is no fullcalendar, you have
to install it separately see the notes in /lib/README

The calendar display uses a higher version of jquery and is incompatible with 
the jquery packaged with drupal, therefore the module searches for the appropriate
version on first run. Once it finds a version then it stores that internally,
if you update fullcalendar after a first install you must run cron for this
variable to be updated if the packaged version of jquery changes, or manually
execute update_fc_jquery_fname(); somehow.

## Todo list

### High Priority
* <strike>Menu items</strike>
* Landing pages for the different available types
* Don't Allow Reservations in the Past
* Make approve / reject moderation ajax callback function
* Pagination or scrolling
* Styles
* Email message to user
* Make title field vs description field
* <strike>Don't show old events</strike>

### Low Priority
* Adjustable time ranges for reservations
* Generalize the set var functions
* Make admin page with list of content for whitelist enable
* Human readable time on the conflict resolution message
* Hook into views and panels, and possible provide block for calendar
* Pull the default colors from a system wide variable/admin setting
* Throw a serialized json error on invalid query (returns empty array now)
* Consider change url scheme to work off of get params instead of url slugs for json queries
* Consider making a separate database table for content calendar colors as these may get large
* Make exclusion an array of ids vs singular id in the conflict lookup
