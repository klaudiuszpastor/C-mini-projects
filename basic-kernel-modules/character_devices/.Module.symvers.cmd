cmd_/home/klaudiusz/Projects/C-mini-projects/basic-kernel-modules/character_devices/Module.symvers :=  sed 's/ko$$/o/'  /home/klaudiusz/Projects/C-mini-projects/basic-kernel-modules/character_devices/modules.order | scripts/mod/modpost -m      -o /home/klaudiusz/Projects/C-mini-projects/basic-kernel-modules/character_devices/Module.symvers -e -i Module.symvers -T - 