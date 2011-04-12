<?php

function cron_alert_status() {
	
	// Get variables
	$to = variable_get('cron_alert_email', 'roger@ossolutions.org');
	$from = variable_get('cron_alert_email_from', 'cron@itworld.com');
	$params['subject'] = variable_get('cron_alert_email_subject', 'Cron Alert');
	$params['body'] = variable_get('cron_alert_email_body', 'Cron run is past due.');
	$show_details = variable_get('cron_alert_show_details', 0);
	$run_cron = variable_get('cron_alert_run_cron', 0);
	$minutes = variable_get('cron_alert_minutes', 20);
	$last_run = variable_get('cron_last', 1);
	$current_time = time();
	$cutoff = $last_run+(1*$minutes*60); // hours*minutes*seconds
	$cron_run = FALSE;
	// end Get variables
		
	if ($show_details) {
		echo 'Cron last ran at: ' . gmdate("M d Y H:i:s", $last_run);
		echo '</br>';
		echo 'Cutoff set to: ' . gmdate("M d Y H:i:s", $cutoff);
		echo '</br>';
		echo 'Current time is: ' . gmdate("M d Y H:i:s", $current_time);
		echo '</br>';
		echo 'Sending email from: ' . $from;
		echo '</br>';
		echo 'Sending email to: ' . $to;
		echo '</br>';
		echo 'Email Subject: ' . $params['subject'];
		echo '</br></br>';
		echo 'Email Body: </br>' . $params['body'];
		echo '</br></br>';
		echo 'Minutes set to: ' . $minutes . ' minutes';
		echo '</br></br>';
	}
	//Verify that the selected number of minutes has passed time already
	if ($cutoff < $current_time) {
        if ($show_details) {
			$error = "Cron run is past due.<br>Check site <a href='/admin/reports/status' target='_blank'>status</a> report.";
			echo $error;
		}
		
		if ($run_cron) {
		// Release the cron last and semaphore.
		variable_del('cron_last');
		variable_del('cron_semaphore');
		$cron_run = drupal_cron_run();
		}
	
		$message = drupal_mail('cron_alert', 'notice', $to, language_default(), $params, $from, TRUE);			
	} else {
		if ($show_details) {
			$details = "Cron run is not past due.<br>Check site <a href='/admin/reports/status' target='_blank'>status</a> report.";
			echo $details;
		}
	}

	return;
}
