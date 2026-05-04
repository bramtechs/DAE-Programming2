# file: package.nix

# The items in the curly brackets are function parameters as this is a Nix
# function that accepts dependency inputs and returns a new package
# description
{
  self
, lib
, llvm
, pkgs
}:

# stdenv.mkDerivation now accepts a list of named parameters that describe
# the package itself.

llvm.libcxxStdenv.mkDerivation {
  name = "CaveStoryPlus";

  # We now list the dependencies similar to the devShell before.
  # Distinguishing between `nativeBuildInputs` (runnable on the host
  # at compile time) and normal `buildInputs` (runnable on target
  # platform at run time) is an important preparation for cross-compilation.
  nativeBuildInputs = with pkgs; [ cmake
                                   pkg-config
                                   ninja
                                   llvm.libcxx
                                   SDL2
                                   SDL2_ttf
                                   SDL2_mixer
                                   SDL2_image
                                   libwebp
                                   libGL
                                   libtiff
                                   libGL];
  
  src = builtins.path {
    path = self;
  };

  enableParallelBuilding = true;

  # Instruct the build process to run tests.
  # The generic builder script of `mkDerivation` handles all the default
  # command lines of several build systems, so it knows how to run our tests.
  doCheck = false;
}
