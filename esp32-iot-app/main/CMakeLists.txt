idf_component_register(SRCS "wifi_app.c" "http_server.c" "main.c" "rgb_led.c" "wifi_app.c" "http_server.c" "dht22.c" "mqtt_app.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES webpage/app.css webpage/app.js webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js)	
                    target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")				