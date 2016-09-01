<?php 
global $base_url;   // Will point to http://www.example.com
global $base_path;  // Will point to at least "/" or the subdirectory where the drupal in 

/**
	* hf_location_bar block callback
	*/
function location_bar_view_page_callback() {
	$getTodaysDate = strtolower(date("l"));
	$path = drupal_get_path('module', 'hf_locations');
	// Using the TableSort Extender is what tells the the query object that we are sorting.
	$query = db_select('node', 't');
	$query->join('field_data_field_branch_' .$getTodaysDate. '', 'day', 't.vid = day.revision_id');
	$query->leftjoin('field_data_field_branch_email', 'email', 't.vid = email.revision_id');
	$query->leftjoin('field_data_field_branch_phone', 'phone', 't.vid = phone.revision_id');
	$query->fields('t', array('title')); 
	$query->fields('day', array('field_branch_' .$getTodaysDate. '_value')); 
	$query->fields('email', array('field_branch_email_email'));
	$query->fields('phone', array('field_branch_phone_number'));
	$query->condition('t.type', 'library_branch', '=');
	$query->condition('t.status', 1, '=');

	// Don't forget to tell the query object how to find the header information.
	$result1 = $query
			->range(0,20)
			->execute();

	 $result2 = $query
			->range(0,20)
			->execute();

	// Build template
	$output = '<div class="location-bar">';
	$output .= '<a class="show-all-locations" data-reveal-id="modal-all-locations"></a>';
	$output .= '<div class="items">';
	$output .= result_template($result1);
	$output .= '</div>';
	$output .= '</div>';
	
	//Modal
	$output .= '<div id="modal-all-locations" class="reveal-modal" data-reveal aria-labelledby="Todays Hours" aria-hidden="true" role="dialog">';
		$output .= '<img src="/'.$path. '/img/img-library.jpg" />';
		$output .= '<div class="items">';
			$output .= '<h2>Today\'s Hours</h2>';
			$output .= '<a class="view-all" href="' .$base_path. '/about/hours">View all details</a>';
			$output .= result_template($result2);
		$output .= '</div>';
	$output .= '</div>';

	// add js
	drupal_add_js($path . '/js/hf_locations.js', array('type' => 'external', 'scope' => 'footer', 'weight' => 1));
	return $output;
}


/**
	* Result items
	*/
function result_template($result) {
	$getTodaysDate = strtolower(date("l"));
	foreach ($result as $r) {
		$day = 'field_branch_'.$getTodaysDate.'_value';
		$output .= '<div class="loc-item">';
			$output .= '<div class="wrap-left">';
				$output .= '<div class="title">' .$r->title. '</div>';
				$output .= '<div class="day">' .$r->$day. '</div>';
				// $output .= '<div class="btn-booking"><a href="javascript:void(0)">Book a Room</a></div>';
			$output .= '</div>';
			$output .= '<div class="wrap-right">';
				$output .= '<div class="number"><span class="lbl">Phone: </span><a href="tel:' .$r->field_branch_phone_number. '">' .$r->field_branch_phone_number. '</a></div>';
				$output .= '<div class="email"><span class="lbl"><a href="mailto:' .$r->field_branch_email_email. '">Email Us</a></span></div>';
			$output .= '</div>';
		$output .= '</div>';
	}
	return $output;
}
