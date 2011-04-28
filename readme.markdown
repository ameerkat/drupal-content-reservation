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
* Created (created)
* Modified (modified)

## Installation Notes
The calendar display uses a higher version of jquery and is incompatible with 
the jquery packaged with drupal, therefore the module searches for the appropriate
version on first run. Once it finds a version then it stores that internally,
if you update fullcalendar after a first install you must run cron for this
variable to be updated if the packaged version of jquery changes, or manually
execute update_fc_jquery_fname(); somehow.

## todo list
* Make admin page with list of content for opt-in enable
* Human readable time on the conflict resolution message
* Hook into views and panels, and possible provide block for calendar
* Pull the default colors from a system wide variable
* Throw a serialized error on invalid query
* Change url scheme to work off of get params instead of url slugs for JSON
* Consider making a separate database table as these may get large
* Append content_reservation_ to the beginning of these so as not to conflict
* Add a main page that lists all content type and map it to a url via hook_menu
* Make the events editable with proper permissions
* Make exclusion an array of ids
