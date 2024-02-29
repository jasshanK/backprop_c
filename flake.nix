{
  description = "backprop in c";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
  };

  outputs = { self, nixpkgs }: {
    devShell.x86_64-linux =
      let
        pkgs = nixpkgs.legacyPackages.x86_64-linux;
      in pkgs.mkShell {
        buildInputs = with pkgs; [
          ccls 

          gcc
          gdb
        ];

        LD_LIBRARY_PATH="${pkgs.stdenv.cc.cc.lib}/lib";
      };
    };
  }
