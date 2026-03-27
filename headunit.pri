CONFIG += plugin link_pkgconfig
PKGCONFIG += libssl libcrypto libusb-1.0 glib-2.0 gobject-2.0
PKGCONFIG += protobuf

# Get the relative path from the build dir to the .pri file dir
# protoc can't distinguish if relative and absolute paths are the same
# This matches the "../../../..." path qmake is generating
RELATIVE_PWD = $$relative_path($$PWD, $$OUT_PWD)

# protobuf definitions
PROTOS = $$PWD/AndroidAuto.proto \
         $$PWD/Bluetooth.proto

PROTO_SRC_DIR = $$PWD/src/protocol
PROTO_INC_DIR = $$PWD/includes/protocol

# Create the custom compiler for protobuf
proto_compiler.name = protoc
proto_compiler.input = PROTOS
proto_compiler.output = $$PROTO_SRC_DIR/${QMAKE_FILE_BASE}.pb.cc

# Use the relative path for --proto_path
# This ensures that --proto_path is an EXACT string prefix of ${QMAKE_FILE_IN}
proto_compiler.commands = $(MKDIR) $$PROTO_SRC_DIR && \
                          $(MKDIR) $$PROTO_INC_DIR && \
                          protoc --proto_path=$$RELATIVE_PWD --cpp_out=$$PROTO_SRC_DIR ${QMAKE_FILE_IN} && \
                          $(MOVE) $$PROTO_SRC_DIR/${QMAKE_FILE_BASE}.pb.h $$PROTO_INC_DIR/

# Add generated protobuf source and headers as dependencies
proto_compiler.CONFIG += target_predeps
proto_compiler.variable_out = SOURCES
proto_compiler.depends = ${QMAKE_FILE_IN}
proto_compiler.dependency_type = TYPE_C

QMAKE_EXTRA_COMPILERS += proto_compiler

SOURCES += \
    $$PWD/src/bluetooth/BluetoothServer.cpp \
    $$PWD/src/bluetooth/BluetoothService.cpp \
    $$PWD/src/hu_aap.cpp \
    $$PWD/src/hu_ssl.cpp \
    $$PWD/src/hu_uti.cpp \
    $$PWD/src/transport/USBTransportStream.cpp \
    $$PWD/src/transport/TCPTransportStream.cpp

INCLUDEPATH += $${PWD}/includes
INCLUDEPATH += $$PROTO_INC_DIR

HEADERS += \
    $$PWD/includes/AndroidAuto.h \
    $$PWD/includes/bluetooth/BluetoothServer.h \
    $$PWD/includes/bluetooth/BluetoothService.h \
    $$PWD/includes/HeadunitEventCallbacks.h \
    $$PWD/includes/defs.h \
    $$PWD/includes/hu_ssl.h \
    $$PWD/includes/hu_uti.h \
    $$PWD/includes/transport/AbstractTransportStream.h \
    $$PWD/includes/transport/USBTransportStream.h \
    $$PWD/includes/transport/TCPTransportStream.h
