# sshmanager
A veeery simple ssh manager, written in C++

- [Description](#Description)
- [Usage](#usage)
- [Contributing](#contributing)
- [Support](#support)
- [License](#license)

## Description

I wrote this to manage my sshs and I thought that open is better, so I posted this on Github.
Manage your sshs, add and remove them and connect to them, without the need to remember a lot of hostnames and usernames.

## Usage 

You can compile this or download directly the binary file. To use this system-wide, place the binary file in /bin folder.

```bash
sshmanager list
# This will list all your saved SSHs

sshmanager add
# Follow the instructions that the CLI gives you to add a new SSH. It is very fast and simple, It has some checks for the validity of the informations too.

sshmanager remove
# Follow the instructions that the CLI gives you to remove a specific SSH.

sshmanager connect
# Follow the instructions that the CLI gives you to connect to a specific SSH.

sshmanager help
# Get more informations about this script
```

## Contributing
This is more a personal project, but if you want to contribute to it, or if you want to fork it, you are welcome to try!

## Support
This is a personal project, but if you need any help, contact me at my mail gianlutara@gmail.com

## License
[MIT](https://github.com/GianlucaTarantino/sshmanager/blob/main/LICENSE)