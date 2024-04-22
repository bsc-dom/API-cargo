Usage:
>pip install /<path>/<to>/<plugin>/dataclay-plugin/requirements.txt 
+Modify (if necessary) the python path and/or it's version at the Makefile
+Add what is needed to the Makefile
+Include the plugin to your code #include "/<path>/<to>/<plugin>/dataclay-plugin/dataclayplugin.h"
>make
>docker compose -f /<path>/<to>/<plugin>/dataclay-plugin/docker-compose.yaml up
>./main
+...
>docker compose -f /<path>/<to>/<plugin>/dataclay-plugin/docker-compose.yaml down

Recompile Shared Object:
>gcc -shared -o libdataclayplugin.so -fPIC -I/usr/include/python<python-version> -L/<path>/<to>/venv/lib python<python-version> dataclay_plugin.c -lpython<python-version>
