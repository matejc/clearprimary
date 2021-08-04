{ pkgs ? import <nixpkgs> {} }:
with pkgs;
stdenv.mkDerivation rec {
  name = "clearprimary";
  src = ./.;
  buildInputs = [ gcc glib.dev gtk3.dev atk.dev pkgconfig ];
  buildPhase = ''
    NIX_CFLAGS_COMPILE="$NIX_CFLAGS_COMPILE $(pkg-config --cflags gtk+-3.0 glib-2.0 gdk-3.0 atk)"
    export NIX_CFLAGS_COMPILE

    NIX_LDFLAGS="$NIX_LDFLAGS $(pkg-config --libs gtk+-3.0 glib-2.0 gdk-3.0 atk)"
    export NIX_LDFLAGS

    gcc -o ${name} clearprimary.c
  '';
  installPhase = ''
    mkdir -p $out/bin
    cp ${name} $out/bin/
  '';
}
