# Simple Mail System

Simple Mail System provides a means for reviewing and updating 
the mail system configuration variables held in the system 
configuration file system.mail.json. This file holds
key/value pairs, the key being a module's mail class and the
value is the identity of the mail system to be used for
sending mail from that module. 

If a module that sends mail does not provide an entry in
system.mail its email will be sent by whatever is set to be
the current default mail system for the site.

If a module needs to be able to indicate a preferred mail system
for sending its email, e.g Mimemail or SMTP, it must provide one or
more key/value pairs in system.mail, the key being a class identity
and the value is the mail system identity.

A module can use more than one value of class if, for example, it needs
to send some mail as plain text and other as HTML. This class is also
used to identify the template for formatting an HTML email. For example, 
the module Views Send uses this to enable use of a different template
for each view it handles.

The mail class identifier provided by the module that is sending email
is comprised of the module name and an optional and additional key 
appended to it. Examples for the webform module might be: 
webform_plain; webform_html. The sending module enters one of these as 
the second parameter '$key' in the call to function backdrop_mail().

This module is a much simplifed alternative to the Mailsystem module.


## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Use the configuration page at /admin/config/system/simple_mailsystem to
  set one available mail system class as the system-wide default and
  the class to use for each email module currently installed.
	
## License

This project is GPL v2 software. See the LICENSE.txt 
file in this directory for complete text.
    
## Maintainer for Backdrop

Graham Oliver (github.com/Graham-72/)



## Acknowledgement

This module for Backdrop re-uses some parts of the Mailsystem module
created for Drupal.
