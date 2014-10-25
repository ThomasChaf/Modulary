class Display:
  HEAD     = "=============TEST============="
  FOOT     = "=============================="
  BLUE     = '\033[96m'
  HEADER   = '\033[95m'
  OKBLUE   = '\033[94m'
  GREEN    = '\033[92m'
  WARNING  = '\033[93m'
  RED      = '\033[91m'
  ENDC     = '\033[0m'

  def __init__(self):
    self.head = False
    self.iserror = False

  def setError(self, error):
    self.iserror = self.iserror or error

  def color(self):
    print(Display.RED if self.iserror else Display.GREEN)

  def header(self):
    if not self.head:
      self.head = True
      self.color()
      print(Display.HEAD)

  def footer(self):
    print(Display.FOOT)
    print(Display.ENDC)

  def error(self, message):
    self.setError(True)
    self.header()
    print(message)

  def summary(self, sucess, total):
    self.setError(sucess != total or sucess == 0)
    self.header()
    if self.error: print()
    print("Success :", sucess, "/", total)
    self.footer()
