<?php

/**
 * @file
 * Administrative form for setting the mail_system variable.
 * config system.mail contains an array in which the key identifies
 * the module class originating the mail and the value
 * is the name of the mail system to send it.
 * The first key is default-system and its value is
 * DefaultMailSystem.
 * see https://api.backdropcms.org/api/backdrop/core!includes!mail.inc/function/backdrop_mail_system/1
 *
 * The purpose of this module is to enable the value of each
 * key to be selected from the available mail systems.
 *
 * First get current mail system settings
 * this will give the current settings for each
 * module class originating mail.
 * Note: classes are added by modules writing to
 * config system.mail
 */
$mail_systems = config_get('system.mail');
$mail_default = $mail_systems['default-system'];

/**
 * Create a list of modules which implement MailSystemInterface.
 * Look for modules that include a class named '...mailsystem'
 * in their hook_autoload_info() implementation.
 */
function &simple_mailsystem_get_options() {
  $mailsystem_options = array();
  // Backdrop solution from https://github.com/backdrop-contrib/mailsystem/issues/1
  foreach (module_implements('autoload_info') as $module) {
    $function = $module . '_autoload_info';
    if ($module) {
      $modulepath = BACKDROP_ROOT . '/' . backdrop_get_path('module', $module);
    }
    $implements = $function();
    foreach ($implements as $mailsystem_name => $path) {
      if (strpos($mailsystem_name, 'MailSystem') and !strpos($mailsystem_name, 'Delegate')) {
        $mailsystem_options[$mailsystem_name] = $mailsystem_name;
      }
    }
  }
  return $mailsystem_options;
}

function simple_mailsystem_admin_settings() {
  $mail_systems = config_get('system.mail');
  $mail_services = &simple_mailsystem_get_options();
  $mail_default = array("default-system" => $mail_systems['default-system']);

  $form['simple_mailsystem'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mail System Settings'),
    '#description' => t('Backdrop provides a default mail system called DefaultMailSystem. Modules such as Mimemail may provide additional systems. </br>Each module using mail provides one or more identifiers, composed of a %module and an optional %key to be supplied with each email being sent, and this is used to decide which mail system to use, also which formatting template if relevant. The following search order is used: <ol><li>The system associated with the %module and %key, if any.</li><li>The system associated with the %module, if any.</li><li>The site-wide default mail system.</li></ol>'),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  $form['simple_mailsystem']['sitewide'] = array(
    '#type' => 'select',
    '#title' => t('Select site-wide <strong>default</strong> mail system.'),
    '#options' => $mail_services,
    '#default_value' => config_get('system.mail', 'default-system'),
  );

  // set mail system used for each originating class
  // as listed in config system.mail.json

  // list mail system classes excluding default
  foreach ($mail_systems as $class => $name) {
    if ($class != 'default-system') {
      $module = $class;
      $title = t('Set mail system for <strong>') . $module . '</strong> class';
      $form['simple_mailsystem'][$class] = array(
        '#type' => 'select',
        '#title' => $title,
        '#options' => $mail_services,
        '#default_value' => $mail_systems[$class],
      );
    }
  }

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  // Return the form
  return $form;
}

/**
 * Process simple_mailsystem_admin_settings form.
 */
function simple_mailsystem_admin_settings_submit($form, &$form_state) {
  // Set site-wide default mail system.
  config_set('system.mail', 'default-system', $form_state['values']['simple_mailsystem']['sitewide']);
  // Set other mail-class/mail-system key-value pairs.
  foreach ($form_state['values']['simple_mailsystem'] as $class => $name) {
    if (!empty($name) && $class != 'sitewide') {
      config_set('system.mail', $class, $name);
    }
  }
  backdrop_set_message(t('The configuration options have been saved.'));
}
