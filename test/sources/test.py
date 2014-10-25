from display import Display
from stream  import Stream

class Test:
  def __init__(self, stream):
    self.display = Display()
    self.stream = Stream(stream)

  def parse(self):
    if not self.stream.line:
      return False
    parse = self.stream.line.split('#')
    if len(parse) == 2:
      try:
        self.result = int(parse[0].rstrip(' '))
        self.message = parse[1].rstrip(' ')
      except:
        return False
      if self.result != 0 and self.result != 1:
        return False
      return True
    return False

  def launch(self):
    sucess = 0
    total = 0
    while self.stream.read():
      if self.parse():
        if self.result == 1:
          sucess += 1
        else:
          self.display.error("Error on" + self.message)
        total += 1
    self.display.summary(sucess, total)
