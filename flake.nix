{
  description = "c_array dev shell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc
          gnumake
          gdb
          valgrind
          clang-tools  # clangd для LSP
        ];

        shellHook = ''
          echo "c_array dev env ready"
          echo "make        — build libarray.a"
          echo "make test   — run tests"
        '';
      };
    };
}
