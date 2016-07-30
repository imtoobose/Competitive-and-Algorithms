# Node:
# initialized with a certain integer value
# optional argument to make a node a leaf (pass Node(-1)) 
class Node:
  def __init__(self, value, *args):
    self._value = value
    if(len(args)>0):
      self._left  = args[0]
      self._right = args[0]
    else:
      self._left  = -1
      self._right = -1

#Tree : 
# values      : all nodes in tree
# tree_source : the root of the tree
# count       : number of nodes
# accessible functions:
# constructor: takes the array to be used in segment tree
# queryRange : get the integer sum of values between two indices
# dfs : print nodes of tree with their neighbors

class Tree:
  def __init__ (self, inputarray):
    endpoint          = Node(-1)
    self._values      = [Node(x, endpoint) for x in inputarray]
    self._tree_source = self.buildtree(0, len(self._values)-1)
    self._count       = len(self._values)

  def buildtree(self, start, end):
    if start==end:
      return self._values[start]
    else:
      leftchild  = self.buildtree(start, (start+end)//2)
      rightchild = self.buildtree((start+end)//2+1, end)
      n          = Node(leftchild._value+rightchild._value)
      n._left    = leftchild
      n._right   = rightchild
      return n

  #wrapper for queryRange
  def queryRange(self, left, right):
    return self._queryRange(self._tree_source, 0, (self._count-1) , left, right)

  #get query between two values by summing up 
  #all segments within left and right
  def _queryRange(self, node, start, end, left, right):
    #if the current node's segment is out of the bounds of our query return 0
    if right < start or left > end:
      return 0
    
    #if the segment queried fits inside current 
    #segment return the segment
    elif left<=start and right>= end:
      return node._value

    #get the regions on the left and right
    else:
      mid= (start+end)//2
      return self._queryRange(node._left, start, mid, left, right) + self._queryRange(node._right, mid+1, end, left, right)

  #wrapper for dfs
  def dfs(self):
    return self._dfs(self._tree_source, 0)

  #print nodes
  def _dfs(self, source, level):
    if(source._left._value==-1 and source._right._value==-1):
      print source._value, level, source._left._value, source._right._value

    else:
      if not source._left._value==-1:
        self._dfs(source._left, level+1)
      if not source._right._value==-1:
        self._dfs(source._right, level+1)
      print source._value, level, source._left._value, source._right._value

t = Tree([1,2,3,4,5,4,5,6])
print str(t.queryRange(3, 6))
