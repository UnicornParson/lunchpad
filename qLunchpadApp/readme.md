# Desktop console app
injects key events to active window accrding key mapping preset

## cmd keys and usage
qLunchpadApp.exe *preset-file*  *portname*

- -h - print help
- -l - list of com ports

### example
```
$ qLunchpadApp.exe -l

COM1
COM2

$ qLunchpadApp.exe photoshop.json COM2
```