import sys

class Stream:
  def __init__(self, filename):
    self.line = False
    try:
      self.content = open(filename)
    except IOError:
        print("Error: Could not open file test.txt")
        sys.exit()

  def read(self):
    self.line = self.content.readline()
    if not self.line:
      return False
    self.line = self.line.rstrip("\n")
    return True
