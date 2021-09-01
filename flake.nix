{
  description = "A simple calculator";

  inputs = {
    futils = {
      type = "github";
      owner = "numtide";
      repo = "flake-utils";
      ref = "master";
    };

    nixpkgs = {
      type = "github";
      owner = "NixOS";
      repo = "nixpkgs";
      ref = "nixos-unstable";
    };

    pre-commit-hooks = {
      type = "github";
      owner = "cachix";
      repo = "pre-commit-hooks.nix";
      ref = "master";
      inputs = {
        flake-utils.follows = "futils";
        nixpkgs.follows = "nixpkgs";
      };
    };
  };

  outputs = { self, futils, nixpkgs, pre-commit-hooks }:
    futils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        checks = {
          inherit (self.packages.${system}) abacus;

          pre-commit = pre-commit-hooks.lib.${system}.run {
            src = self;

            hooks = {
              nixpkgs-fmt = {
                enable = true;
              };

              clang-format = {
                enable = true;
                name = "clang-format";
                entry = "${pkgs.clang-tools}/bin/clang-format -style=file -i";
                types = [ "text" "c++" ];
                language = "system";
              };
            };
          };
        };

        defaultPackage = self.packages.${system}.abacus;

        devShell = pkgs.mkShell {
          inherit (self.defaultPackage.${system})
            checkInputs
            nativeBuildInputs
            ;

          inherit (self.checks.${system}.pre-commit) shellHook;
        };

        packages = futils.lib.flattenTree {
          abacus = pkgs.stdenv.mkDerivation {
            pname = "abacus";
            version = "0.0.0";

            src = self;

            nativeBuildInputs = with pkgs; [
              bison
              cmake
              flex
              ninja
              pkg-config
            ];

            checkInputs = with pkgs; [
              gtest
            ];

            doCheck = true;

            meta = with pkgs.lib; {
              description = "A simple calculator using big numbers";
              homepage = "https://gitea.belanyi.fr/ambroisie/abacus";
              license = licenses.mit;
              maintainers = [ ambroisie ];
              platforms = platforms.unix;
            };
          };
        };
      });
}
