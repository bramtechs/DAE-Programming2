{
  description = "Programming 2 'Cave Story Plus'";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ self, flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      # This is the list of architectures that work with this project
      systems = [
        "x86_64-linux"
      ];
      perSystem = { config, self', inputs', pkgs, system, ... }:
        let
          pkgs = import inputs.nixpkgs {
            inherit system;
            config.allowUnfree = true;
          };

          llvm = pkgs.llvmPackages_22;
        in {
          packages.cavestoryplus = pkgs.callPackage ./package.nix {
            inherit self llvm pkgs;
          };

	        packages.default = pkgs.writeShellScriptBin "RunCaveStoryPlus" ''
      exec nix --extra-experimental-features "nix-command flakes" run --impure github:nix-community/nixGL -- ${config.packages.cavestoryplus}/bin/CaveStoryPlus
    '';

          devShells.default = pkgs.mkShell {
            inputsFrom = [ config.packages.cavestoryplus ];
            packages = with pkgs; [
              config.packages.default
              cmake
              llvm.clang-tools
              ripgrep
            ];
          };
        };
    };
}
