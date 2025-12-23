import Lake
open Lake DSL


package mylean where

require mathlib from git
  "https://github.com/leanprover-community/mathlib4" @ "master"

lean_exe myleanExe {
  root := `Main
}
