

BOX_Y = 50;
BOX_X = 100;
BOX_Z = 2;

BOX_GROUND_Z = 15;

USB_PCB_SIZE_X = 14.9;
USB_PCB_SIZE_Y = 13.5;
USB_PCB_SIZE_Z =  2.5;

USB_CONN_X = 6.1;
USB_CONN_Y = 8.0;
USB_CONN_Z = 2.3;

module usb_breakout() {
    union() {
        difference() {
            translate([0, -1.5, 0]) cube([17, 16, 6]);
            translate([-0.1, 0, -0.1]) {
                cube([USB_PCB_SIZE_X + 0.1, USB_PCB_SIZE_Y, USB_PCB_SIZE_Z + 0.1]);
            }
            BOX_A = USB_PCB_SIZE_Y / 2 - USB_CONN_Y /2;
            translate([-0.1, BOX_A, USB_PCB_SIZE_Z - 0.1]) {
                cube([USB_CONN_X + 0.1, USB_CONN_Y, USB_CONN_Z + 0.1]);
            }
        }
        translate([7.5, 2, -0.5]) {
            cylinder(d=2.5, h=4, $fn=80);
        }
        translate([7.5, USB_PCB_SIZE_Y - 2.5, -0.5]) {
            cylinder(d=2.5, h=4, $fn=80);
        }
    }
}

module stand() {
    union() {
        translate([20/2, 20/2, 0]) {
            cylinder(d=20, h=2, $fn=100);
        }
        translate([1.,1.2, 0]) {
            cube([8, 8, 2]);
        }
    }
}

union() {
    difference() {
        cube([BOX_X, BOX_Y, BOX_Z]);
        translate([BOX_X/ 2, BOX_Y/ 2, 1]) {
            cylinder(h=10, d=5, center=true, $fn=100);
        }
        translate([10, BOX_Y/ 2, 1]) {
            cylinder(h=10, d=7.5, center=true, $fn=100);
        }
    }
    translate([0, 0, -BOX_GROUND_Z]) {
        difference() {
            cube([BOX_X, BOX_Y, BOX_GROUND_Z]);
            translate([1.2, 1.2, -1]) {
                cube([BOX_X-2.4, BOX_Y- 2.4, BOX_GROUND_Z +1]);
            }
            translate([BOX_X/2 - 6, -1, 9.5]) {
                cube([15, 20, 6]);
            }
        }
    }
    translate([BOX_X/2 + 16/2, 0, -6]) {
        rotate([0, 0, 90]) usb_breakout();
    }
    
    translate([0, 0, -15]) {
        stand();
    }
    translate([BOX_X, 0, -15 +2]) {
        rotate([0, 180, 0]) stand();
    }
    translate([0, BOX_Y, -15 +2]) {
        rotate([180, 0, 0]) stand();
    }
    translate([BOX_X, BOX_Y, -15]) {
        rotate([0, 0, 180]) stand();
    }
}