<img align="right" src="./logo_hpcp_small.png">

#HPCP

<br clear="right"/>

HPCP (High Precision Computation Program) is a library that I'm currently trying to devellop that will be able to accuratly do calculations with minimal amounts of RAM (whilst using temp files on the hardrive).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

To build HPCP it is better to use the ```make``` command. If your on linux you should already have it but on windows your will have to install it. I recommand installing it througt "chocolatey"
To install chocolatey copy and paste the first command into a windows powershell with admin powers (jsut search powershell in the windows shearch bar). Then paste the second command to install make.

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
choco install make
```

You can check if the installation was successful by typing ```make``` into a cmd. It should output ```make: *** No targets specified and no makefile found.  Stop.```.

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

To check if the build was successfully done you can type ```make check``` (/!\ not implemented yet !)

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

*plain old C with gcc

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

*I had problems with GNU MPFR and GNU MP so I am makin my own calculation software. 

