
class Stack:
    """A container with a first-in-first-out (FIFO) queuing policy."""

    def __init__(self):
        self.list = []

    def push(self, item):

        self.list.insert(0, item)

    def pop(self):
        return self.list.pop(0)

    def isEmpty(self):
        "Returns true if the queue is empty"
        return len(self.list) == 0
