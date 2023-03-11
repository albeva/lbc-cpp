'' #include <stdio.h>
''
'' int main() {
''     puts("Hello World\n");
''     return EXIT_SUCCESS;
'' }
''
[header="stdio.h", transient=true] _
Extern "C"
    Declare Function puts(str As ZString) As Integer
End Extern

puts "Hello World\n"
