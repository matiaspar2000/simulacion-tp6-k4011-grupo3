# simulacion-tp6-k4011-grupo3

Código para ambos modelos del sistema de atención de alumnos de Sistemas Operativos. Permite ejecutar ambos modelos con distintos valores de N, los cuales para el trabajo desarrollado fueron establecidos para que vayan de 2 a 10 ayudantes.

Por motivos de facilitar la implementación el código tiene pequeñas diferencias respecto de los respectivos diagramas.

1. N puestos 1 cola (modelo basado en el sistema actual)

-Variables Exógenas
  Control: cantidad (Cantidad de Ayudantes, personas)
  Datos: IA (Intervalo de Arribos, segundos); TA (Tiempo de Atención, segundos)

-Variables Endógenas
  Estado: NS (Cantidad de Estudiantes en el sistema, personas)
  Resultado: PTO (Porcentaje de Tiempo Ocioso de los Ayudantes);
             PTE (Promedio de Tiempo de Espera en Cola, segundos)
            
            
            
2. N puestos N colas (alternativa propuesta)

-Variables Exógenas
  Control: cantidad (Cantidad de Ayudantes, personas)
  Datos: IA (Intervalo de Arribos, segundos); TA (Tiempo de Atención, segundos)

-Variables Endógenas
  Estado: NS[i] (Cantidad de Estudiantes en el sistema, personas)
  Resultado: PTO (Porcentaje de Tiempo Ocioso de los Ayudantes);
             PTE (Promedio de Tiempo de Espera en Cola, segundos)
             
            
            
