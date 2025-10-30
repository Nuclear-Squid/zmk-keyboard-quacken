{
  description = "Development flake for the Quacken’s ZMK firmware";
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let pkgs = nixpkgs.legacyPackages.x86_64-linux; in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        (python3.withPackages (py-pkgs: with py-pkgs; [
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
            west
        ]))
        ninja
      ];
    };
  };
}
