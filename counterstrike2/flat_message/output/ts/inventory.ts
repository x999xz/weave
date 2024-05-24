// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class Inventory implements flatbuffers.IUnpackableObject<InventoryT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):Inventory {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsInventory(bb:flatbuffers.ByteBuffer, obj?:Inventory):Inventory {
  return (obj || new Inventory()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsInventory(bb:flatbuffers.ByteBuffer, obj?:Inventory):Inventory {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new Inventory()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

itemId():bigint {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : BigInt('0');
}

mutate_item_id(value:bigint):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 4);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeUint64(this.bb_pos + offset, value);
  return true;
}

team():number {
  const offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_team(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 6);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

slot():number {
  const offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_slot(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 8);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

static startInventory(builder:flatbuffers.Builder) {
  builder.startObject(3);
}

static addItemId(builder:flatbuffers.Builder, itemId:bigint) {
  builder.addFieldInt64(0, itemId, BigInt('0'));
}

static addTeam(builder:flatbuffers.Builder, team:number) {
  builder.addFieldInt32(1, team, 0);
}

static addSlot(builder:flatbuffers.Builder, slot:number) {
  builder.addFieldInt32(2, slot, 0);
}

static endInventory(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createInventory(builder:flatbuffers.Builder, itemId:bigint, team:number, slot:number):flatbuffers.Offset {
  Inventory.startInventory(builder);
  Inventory.addItemId(builder, itemId);
  Inventory.addTeam(builder, team);
  Inventory.addSlot(builder, slot);
  return Inventory.endInventory(builder);
}

unpack(): InventoryT {
  return new InventoryT(
    this.itemId(),
    this.team(),
    this.slot()
  );
}


unpackTo(_o: InventoryT): void {
  _o.itemId = this.itemId();
  _o.team = this.team();
  _o.slot = this.slot();
}
}

export class InventoryT implements flatbuffers.IGeneratedObject {
constructor(
  public itemId: bigint = BigInt('0'),
  public team: number = 0,
  public slot: number = 0
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  return Inventory.createInventory(builder,
    this.itemId,
    this.team,
    this.slot
  );
}
}
