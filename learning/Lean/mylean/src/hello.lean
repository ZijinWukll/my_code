/- Lean 入门示例：输出 Hello, Lean! -/
/- main 函数是 Lean 程序的入口 -/
def main : IO Unit := do
  -- 输出一行欢迎信息
  IO.println "Hello, Lean!"
