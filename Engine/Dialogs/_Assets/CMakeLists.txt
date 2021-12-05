
set(src "${CMAKE_CURRENT_SOURCE_DIR}")
set(bin "${CMAKE_CURRENT_BINARY_DIR}")

IMPORTER_TARGET(DialogsAssets
    -loadimage "${src}/bubble.png"
    -transparent 0xfe00fe

    -startbank 6

    -area8x8 2 0
    -outbitmap BubbleTopArrow

    -area8x8 0 1
    -outbitmap BubbleTopLeft
    -area8x8 1 1
    -outbitmap BubbleTop
    -area8x8 2 1
    -outbitmap BubbleTopHole
    -area8x8 3 1
    -outbitmap BubbleTopRight

    -area8x8 0 2
    -outbitmap BubbleLeft
    -area8x8 1 2
    -outbitmap BubbleCenter
    -area8x8 3 2
    -outbitmap BubbleRight

    -area8x8 0 3
    -outbitmap BubbleBottomLeft
    -area8x8 1 3
    -outbitmap BubbleBottom
    -area8x8 2 3
    -outbitmap BubbleBottomHole
    -area8x8 3 3
    -outbitmap BubbleBottomRight

    -area8x8 2 4
    -outbitmap BubbleBottomArrow

    -outsymlist "${bin}/BubbleBitmaps.h"
    )
