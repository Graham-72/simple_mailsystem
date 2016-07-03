# Simple Mail System

Simple Mail System provides a means for updating the mail system
configuration variables.

Normally a contributed module that needs to be able to send
email, for example Views Send, will set its required values
in the core config file system.mail.json.

This module enables a site's default mail system to be selected
from the available options, similarly the mail system may be
assigned for each source of email. So, for example, for
Views Send each individual view may be assigned a choice of mail system.

This is a much simplifed alternative to the Mailsystem module.


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