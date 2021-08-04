{ pkgs ? import <nixpkgs> {} }:
with pkgs;
let
  buildCmd = "gcc -o clearprimary $(pkg-config --cflags --libs gtk+-3.0 glib-2.0 gdk-3.0 atk) clearprimary.c";
in
stdenv.mkDerivation rec {
  name = "clearprimary";
  src = ./.;
  buildInputs = [ coreutils gcc glib.dev gtk3.dev atk.dev pkgconfig ];
  buildPhase = ''
    ${buildCmd}
  '';
  installPhase = ''
    mkdir -p $out/bin
    cp ${name} $out/bin/
  '';
  shellHook = ''
    ${bear}/bin/bear -- ${buildCmd}
  '';
}
