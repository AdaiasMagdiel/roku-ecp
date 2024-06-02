# Roku ECP Remote Control

This C program allows you to communicate with Roku devices, such as TVs, and simulate a remote control with enhanced access using the Roku External Control Protocol (ECP).

## Features

- Control your Roku device using a command-line interface.
- Supports various remote control keys, including power, volume, and navigation.

## Installation

1. **Clone this repository:**
   ```sh
   git clone https://github.com/AdaiasMagdiel/roku-ecp.git
   ```
2. **Compile the project:**
   Ensure you have `gcc` and `make` installed, then run:
   ```sh
   make
   ```
   > **Note for Windows users:** You can use [W64DevKit](https://github.com/skeeto/w64devkit/) to compile the project.
3. **Run the program:**
   ```sh
   ./rokuecp
   ```
   Running `rokuecp` without arguments will display usage instructions.

>[!NOTE]
> **Note:** This project is tailored for Windows but will likely compile on Linux with some modifications.

## Configuration

1. **Update the HOST:**
   Change the `HOST` in `main.c` to your Roku device's IP address.
2. **Update the PORT:**
   The default port is `8060`. Change it only if your Roku device uses a different port.

## Contributing

Contributions are welcome! You can:

- Fork the repository
- Create a new branch (`git checkout -b feature-branch`)
- Commit your changes (`git commit -am 'Add new feature'`)
- Push to the branch (`git push origin feature-branch`)
- Open a Pull Request

Feel free to open issues or send pull requests for any bugs or feature requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
