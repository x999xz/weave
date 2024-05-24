// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class Item implements flatbuffers.IUnpackableObject<ItemT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):Item {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsItem(bb:flatbuffers.ByteBuffer, obj?:Item):Item {
  return (obj || new Item()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsItem(bb:flatbuffers.ByteBuffer, obj?:Item):Item {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new Item()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

itemDef():number {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_item_def(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 4);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

paintName():string|null
paintName(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
paintName(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

name():string|null
name(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
name(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

skinKey():bigint {
  const offset = this.bb!.__offset(this.bb_pos, 10);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : BigInt('0');
}

mutate_skin_key(value:bigint):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 10);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeUint64(this.bb_pos + offset, value);
  return true;
}

paintId():number {
  const offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_paint_id(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 12);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

rariry():number {
  const offset = this.bb!.__offset(this.bb_pos, 14);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_rariry(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 14);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

textureId():number {
  const offset = this.bb!.__offset(this.bb_pos, 16);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_texture_id(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 16);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

type():number {
  const offset = this.bb!.__offset(this.bb_pos, 18);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_type(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 18);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

pathImage():string|null
pathImage(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
pathImage(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 20);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

isInitilization():boolean {
  const offset = this.bb!.__offset(this.bb_pos, 22);
  return offset ? !!this.bb!.readInt8(this.bb_pos + offset) : false;
}

mutate_is_initilization(value:boolean):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 22);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt8(this.bb_pos + offset, +value);
  return true;
}

paintSeed():number {
  const offset = this.bb!.__offset(this.bb_pos, 24);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_paint_seed(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 24);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

paintWear():number {
  const offset = this.bb!.__offset(this.bb_pos, 26);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_paint_wear(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 26);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stattrack():number {
  const offset = this.bb!.__offset(this.bb_pos, 28);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stattrack(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 28);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stickers0():number {
  const offset = this.bb!.__offset(this.bb_pos, 30);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stickers_0(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 30);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stickers1():number {
  const offset = this.bb!.__offset(this.bb_pos, 32);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stickers_1(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 32);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stickers2():number {
  const offset = this.bb!.__offset(this.bb_pos, 34);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stickers_2(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 34);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stickers3():number {
  const offset = this.bb!.__offset(this.bb_pos, 36);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stickers_3(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 36);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

stickers4():number {
  const offset = this.bb!.__offset(this.bb_pos, 38);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_stickers_4(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 38);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

customName():string|null
customName(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
customName(optionalEncoding?:any):string|Uint8Array|null {
  const offset = this.bb!.__offset(this.bb_pos, 40);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
}

id():bigint {
  const offset = this.bb!.__offset(this.bb_pos, 42);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : BigInt('0');
}

mutate_id(value:bigint):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 42);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeUint64(this.bb_pos + offset, value);
  return true;
}

static startItem(builder:flatbuffers.Builder) {
  builder.startObject(20);
}

static addItemDef(builder:flatbuffers.Builder, itemDef:number) {
  builder.addFieldInt32(0, itemDef, 0);
}

static addPaintName(builder:flatbuffers.Builder, paintNameOffset:flatbuffers.Offset) {
  builder.addFieldOffset(1, paintNameOffset, 0);
}

static addName(builder:flatbuffers.Builder, nameOffset:flatbuffers.Offset) {
  builder.addFieldOffset(2, nameOffset, 0);
}

static addSkinKey(builder:flatbuffers.Builder, skinKey:bigint) {
  builder.addFieldInt64(3, skinKey, BigInt('0'));
}

static addPaintId(builder:flatbuffers.Builder, paintId:number) {
  builder.addFieldInt32(4, paintId, 0);
}

static addRariry(builder:flatbuffers.Builder, rariry:number) {
  builder.addFieldInt32(5, rariry, 0);
}

static addTextureId(builder:flatbuffers.Builder, textureId:number) {
  builder.addFieldInt32(6, textureId, 0);
}

static addType(builder:flatbuffers.Builder, type:number) {
  builder.addFieldInt32(7, type, 0);
}

static addPathImage(builder:flatbuffers.Builder, pathImageOffset:flatbuffers.Offset) {
  builder.addFieldOffset(8, pathImageOffset, 0);
}

static addIsInitilization(builder:flatbuffers.Builder, isInitilization:boolean) {
  builder.addFieldInt8(9, +isInitilization, +false);
}

static addPaintSeed(builder:flatbuffers.Builder, paintSeed:number) {
  builder.addFieldInt32(10, paintSeed, 0);
}

static addPaintWear(builder:flatbuffers.Builder, paintWear:number) {
  builder.addFieldInt32(11, paintWear, 0);
}

static addStattrack(builder:flatbuffers.Builder, stattrack:number) {
  builder.addFieldInt32(12, stattrack, 0);
}

static addStickers0(builder:flatbuffers.Builder, stickers0:number) {
  builder.addFieldInt32(13, stickers0, 0);
}

static addStickers1(builder:flatbuffers.Builder, stickers1:number) {
  builder.addFieldInt32(14, stickers1, 0);
}

static addStickers2(builder:flatbuffers.Builder, stickers2:number) {
  builder.addFieldInt32(15, stickers2, 0);
}

static addStickers3(builder:flatbuffers.Builder, stickers3:number) {
  builder.addFieldInt32(16, stickers3, 0);
}

static addStickers4(builder:flatbuffers.Builder, stickers4:number) {
  builder.addFieldInt32(17, stickers4, 0);
}

static addCustomName(builder:flatbuffers.Builder, customNameOffset:flatbuffers.Offset) {
  builder.addFieldOffset(18, customNameOffset, 0);
}

static addId(builder:flatbuffers.Builder, id:bigint) {
  builder.addFieldInt64(19, id, BigInt('0'));
}

static endItem(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createItem(builder:flatbuffers.Builder, itemDef:number, paintNameOffset:flatbuffers.Offset, nameOffset:flatbuffers.Offset, skinKey:bigint, paintId:number, rariry:number, textureId:number, type:number, pathImageOffset:flatbuffers.Offset, isInitilization:boolean, paintSeed:number, paintWear:number, stattrack:number, stickers0:number, stickers1:number, stickers2:number, stickers3:number, stickers4:number, customNameOffset:flatbuffers.Offset, id:bigint):flatbuffers.Offset {
  Item.startItem(builder);
  Item.addItemDef(builder, itemDef);
  Item.addPaintName(builder, paintNameOffset);
  Item.addName(builder, nameOffset);
  Item.addSkinKey(builder, skinKey);
  Item.addPaintId(builder, paintId);
  Item.addRariry(builder, rariry);
  Item.addTextureId(builder, textureId);
  Item.addType(builder, type);
  Item.addPathImage(builder, pathImageOffset);
  Item.addIsInitilization(builder, isInitilization);
  Item.addPaintSeed(builder, paintSeed);
  Item.addPaintWear(builder, paintWear);
  Item.addStattrack(builder, stattrack);
  Item.addStickers0(builder, stickers0);
  Item.addStickers1(builder, stickers1);
  Item.addStickers2(builder, stickers2);
  Item.addStickers3(builder, stickers3);
  Item.addStickers4(builder, stickers4);
  Item.addCustomName(builder, customNameOffset);
  Item.addId(builder, id);
  return Item.endItem(builder);
}

unpack(): ItemT {
  return new ItemT(
    this.itemDef(),
    this.paintName(),
    this.name(),
    this.skinKey(),
    this.paintId(),
    this.rariry(),
    this.textureId(),
    this.type(),
    this.pathImage(),
    this.isInitilization(),
    this.paintSeed(),
    this.paintWear(),
    this.stattrack(),
    this.stickers0(),
    this.stickers1(),
    this.stickers2(),
    this.stickers3(),
    this.stickers4(),
    this.customName(),
    this.id()
  );
}


unpackTo(_o: ItemT): void {
  _o.itemDef = this.itemDef();
  _o.paintName = this.paintName();
  _o.name = this.name();
  _o.skinKey = this.skinKey();
  _o.paintId = this.paintId();
  _o.rariry = this.rariry();
  _o.textureId = this.textureId();
  _o.type = this.type();
  _o.pathImage = this.pathImage();
  _o.isInitilization = this.isInitilization();
  _o.paintSeed = this.paintSeed();
  _o.paintWear = this.paintWear();
  _o.stattrack = this.stattrack();
  _o.stickers0 = this.stickers0();
  _o.stickers1 = this.stickers1();
  _o.stickers2 = this.stickers2();
  _o.stickers3 = this.stickers3();
  _o.stickers4 = this.stickers4();
  _o.customName = this.customName();
  _o.id = this.id();
}
}

export class ItemT implements flatbuffers.IGeneratedObject {
constructor(
  public itemDef: number = 0,
  public paintName: string|Uint8Array|null = null,
  public name: string|Uint8Array|null = null,
  public skinKey: bigint = BigInt('0'),
  public paintId: number = 0,
  public rariry: number = 0,
  public textureId: number = 0,
  public type: number = 0,
  public pathImage: string|Uint8Array|null = null,
  public isInitilization: boolean = false,
  public paintSeed: number = 0,
  public paintWear: number = 0,
  public stattrack: number = 0,
  public stickers0: number = 0,
  public stickers1: number = 0,
  public stickers2: number = 0,
  public stickers3: number = 0,
  public stickers4: number = 0,
  public customName: string|Uint8Array|null = null,
  public id: bigint = BigInt('0')
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  const paintName = (this.paintName !== null ? builder.createString(this.paintName!) : 0);
  const name = (this.name !== null ? builder.createString(this.name!) : 0);
  const pathImage = (this.pathImage !== null ? builder.createString(this.pathImage!) : 0);
  const customName = (this.customName !== null ? builder.createString(this.customName!) : 0);

  return Item.createItem(builder,
    this.itemDef,
    paintName,
    name,
    this.skinKey,
    this.paintId,
    this.rariry,
    this.textureId,
    this.type,
    pathImage,
    this.isInitilization,
    this.paintSeed,
    this.paintWear,
    this.stattrack,
    this.stickers0,
    this.stickers1,
    this.stickers2,
    this.stickers3,
    this.stickers4,
    customName,
    this.id
  );
}
}
