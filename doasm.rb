class Arg
  def ireg=(number)
    @direct=false
	@register=true
	@value=number
  end
  def reg=(number)
    @direct=true
	@register=true
	@value=number
  end
  def value=(number)
    @direct=true
	@register=false
	@value=number
  end
  def mem=(number)
    @direct=false
	@register=false
	@value=number
  end
end

class X
  def initialize(name)
    @name=name
  end
  def get
    ["i",@name]
  end
  def size
	 1
  end
end

class U
  def initialize(val)
    @val=val
  end
  def get
    ["u",@name]
  end
  def size
    1
  end
end

class Generator
  def ci(name,arg0,arg1)
    f=0
    f|=1 if arg0.direct?
    f|=2 if arg0.register?
    f|=4 if arg1.direct?
    f|=8 if arg1.register?
    [X.new(name),U.new(f),U.new(arg0.value),U.new(arg1.value)]
  end
  def cs(string)
    S.new(string)
  end
end

class ASM
  def initialize()
    @code=[]
  end
  
  def asm(input)
  
  end
end