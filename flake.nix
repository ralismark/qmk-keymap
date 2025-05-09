{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable"; # or "nixpkgs/nixos-22.05"
    flake-utils.url = "github:numtide/flake-utils";

    # must be git not github for submodules
    qmk_firmware = { url = "git+https://github.com/qmk/qmk_firmware?submodules=1&shallow=1"; flake = false; };
  };

  outputs = { self, nixpkgs, flake-utils, qmk_firmware }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      rec {
        # TODO could probably make this a standalone thing
        packages.firmware = pkgs.stdenv.mkDerivation rec {
          name = "firmware.hex";
          src = qmk_firmware;

          buildInputs = with pkgs; [
            qmk
          ];

          postUnpack = ''
            ln -s ${./.} $sourceRoot/keyboards/keebio/nyquist/keymaps/alternate
          '';

          buildPhase = ''
            make keebio/nyquist/rev2:alternate SKIP_GIT=1
          '';

          installPhase = ''
            cp keebio_nyquist_rev2_alternate.hex $out
          '';
        };

        packages.flash = pkgs.writeScript "qmk-flash" ''
          #!/bin/sh
          cd ${qmk_firmware}
          ${pkgs.qmk}/bin/qmk flash ${packages.firmware}
        '';

        apps.flash = {
          type = "app";
          program = "${packages.flash}";
        };

        # Defaults =======================

        packages.default = packages.firmware;
        apps.default = apps.flash;
      });
}
