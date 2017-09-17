def parse_arg(argName, argValue):
   if not argValue.startswith(f'{argName}='):
      raise ValueError(f"Argument '{argValue}' does not start with '{argName}='")
   indexOfFirstEqualsSign = argValue.index('=')
   parsedArgValue = argValue[indexOfFirstEqualsSign + 1:]
   return parsedArgValue
