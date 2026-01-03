{
  description = "Development flake for the Quacken’s ZMK firmware";
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
    self-pkgs = self.packages.x86_64-linux;
  in {
    packages.x86_64-linux.python = (pkgs.python3.withPackages (
      pypkgs: with pypkgs; [
        west
        pyelftools
        pyyaml
        pykwalify
        canopen
        packaging
        progress
        psutil
        pylink-square
        pyserial
        requests
        anytree
        intelhex
      ]
    ));

    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        self-pkgs.python
        cmake
        ninja
        dfu-util
        minicom
      ];
    };
  };
}
