{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
    #nixgl.url = "github:nix-community/nixGL";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        #overlays = [ nixgl.overlay ];
      };
    in {
      devShells.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc
          gdb

          clang-tools
          bear
        ];
      };
    }
  );
}
